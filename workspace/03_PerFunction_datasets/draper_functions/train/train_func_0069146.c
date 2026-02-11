gst_mxf_demux_handle_partition_pack (GstMXFDemux * demux, const MXFUL * key,
    GstBuffer * buffer)
{
  MXFPartitionPack partition;
  GList *l;
  GstMXFDemuxPartition *p = NULL;

  GST_DEBUG_OBJECT (demux,
      "Handling partition pack of size %u at offset %"
      G_GUINT64_FORMAT, GST_BUFFER_SIZE (buffer), demux->offset);

  for (l = demux->partitions; l; l = l->next) {
    GstMXFDemuxPartition *tmp = l->data;

    if (tmp->partition.this_partition + demux->run_in == demux->offset &&
        tmp->partition.major_version == 0x0001) {
      GST_DEBUG_OBJECT (demux, "Partition already parsed");
      p = tmp;
      goto out;
    }
  }


  if (!mxf_partition_pack_parse (key, &partition,
          GST_BUFFER_DATA (buffer), GST_BUFFER_SIZE (buffer))) {
    GST_ERROR_OBJECT (demux, "Parsing partition pack failed");
    return GST_FLOW_ERROR;
  }

  if (partition.this_partition != demux->offset + demux->run_in) {
    GST_WARNING_OBJECT (demux, "Partition with incorrect offset");
    partition.this_partition = demux->offset + demux->run_in;
  }

  if (partition.type == MXF_PARTITION_PACK_HEADER)
    demux->footer_partition_pack_offset = partition.footer_partition;

  for (l = demux->partitions; l; l = l->next) {
    GstMXFDemuxPartition *tmp = l->data;

    if (tmp->partition.this_partition + demux->run_in == demux->offset) {
      p = tmp;
      break;
    }
  }

  if (p) {
    mxf_partition_pack_reset (&p->partition);
    memcpy (&p->partition, &partition, sizeof (MXFPartitionPack));
  } else {
    p = g_new0 (GstMXFDemuxPartition, 1);
    memcpy (&p->partition, &partition, sizeof (MXFPartitionPack));
    demux->partitions =
        g_list_insert_sorted (demux->partitions, p,
        (GCompareFunc) gst_mxf_demux_partition_compare);
  }

  for (l = demux->partitions; l; l = l->next) {
    GstMXFDemuxPartition *a, *b;

    if (l->next == NULL)
      break;

    a = l->data;
    b = l->next->data;

    b->partition.prev_partition = a->partition.this_partition;
  }

out:
  demux->current_partition = p;

  return GST_FLOW_OK;
}
