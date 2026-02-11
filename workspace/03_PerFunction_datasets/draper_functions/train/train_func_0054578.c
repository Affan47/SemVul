bgav_mxf_preface_dump(int indent, mxf_preface_t * s)
  {
  int i;
  do_indent(indent);   bgav_dprintf("Preface:\n");
  bgav_diprintf(indent+2, "UID:                  ");dump_ul(s->common.uid);
  bgav_diprintf(indent+2, "Generation UL:        ");dump_ul(s->common.generation_ul);
  bgav_diprintf(indent+2, "Last modified date:    ");dump_date(s->last_modified_date); bgav_dprintf("\n");
  bgav_diprintf(indent+2, "Version:               %d\n", s->version);
  bgav_diprintf(indent+2, "ObjectModelVersion:    %d\n", s->object_model_version);
  bgav_diprintf(indent+2, "Identifications:       %d\n", s->num_identification_refs);
  for(i = 0; i < s->num_identification_refs; i++)
    {
    do_indent(indent+4); dump_ul_ptr(s->identification_refs[i], s->identifications[i]);
    }
  bgav_diprintf(indent+2, "Content storage:       ");dump_ul_ptr(s->content_storage_ref, s->content_storage);
  bgav_diprintf(indent+2, "Operational pattern:   ");dump_ul_nb(s->operational_pattern_ul);bgav_dprintf(" %s\n", get_op_name(s->operational_pattern));
  bgav_diprintf(indent+2, "Essence containers:    %d\n", s->num_essence_container_types);
  for(i = 0; i < s->num_essence_container_types; i++)
    {
    bgav_diprintf(indent+4, "Essence containers: "); dump_ul(s->essence_container_types[i]);
    }
  bgav_diprintf(indent+2, "Primary package:      ");dump_ul(s->primary_package_ul);

  }
