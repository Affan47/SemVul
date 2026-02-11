m_qid(pIIR_Declaration d, RegionStack &rstack, id_type obj_access)
{
  return qid(d->declarative_region, rstack, obj_access) + "_" + nid(d, obj_access);
}
