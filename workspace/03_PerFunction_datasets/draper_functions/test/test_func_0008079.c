atom_hdlr_set_type (AtomHDLR * hdlr, AtomsContext * context, guint32 comp_type,
    guint32 hdlr_type)
{
  if (context->flavor == ATOMS_TREE_FLAVOR_MOV) {
    hdlr->component_type = comp_type;
  }
  hdlr->handler_type = hdlr_type;
}
