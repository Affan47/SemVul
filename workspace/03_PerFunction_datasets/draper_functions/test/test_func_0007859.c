atom_minf_init (AtomMINF * minf, AtomsContext * context)
{
  atom_header_set (&minf->header, FOURCC_minf, 0, 0);

  minf->vmhd = NULL;
  minf->smhd = NULL;
  minf->hmhd = NULL;

  if (context->flavor == ATOMS_TREE_FLAVOR_MOV) {
    minf->hdlr = atom_hdlr_new ();
    minf->hdlr->component_type = FOURCC_dhlr;
    minf->hdlr->handler_type = FOURCC_alis;
  } else {
    minf->hdlr = NULL;
  }
  atom_dinf_init (&minf->dinf, context);
  atom_stbl_init (&minf->stbl);
}
