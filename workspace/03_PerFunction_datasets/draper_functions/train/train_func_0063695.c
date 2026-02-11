create_SDS(int32 sd_id, int32 nt, struct Input *in)
{
    int32	sds_id;

    if (in->rank == 2)
      {
	int32 edges[2];
	edges[0] = in->dims[1];
	edges[1] = in->dims[0];
	sds_id = SDcreate (sd_id, NULL, nt, in->rank, edges);
      }
    else
      {
	int32 edges[3];
	edges[0] = in->dims[2];
	edges[1] = in->dims[1];
	edges[2] = in->dims[0];
	sds_id = SDcreate (sd_id, NULL, nt, in->rank, edges);
      }
    return(sds_id);
}
