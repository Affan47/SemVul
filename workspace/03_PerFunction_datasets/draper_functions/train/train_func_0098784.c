init( const Spgr_descr& spgr_descr )
{

  hash_ = spgr_descr.hash();
  generators_ = spgr_descr.generator_ops();

  cacheref = ClipperInstantiator::instance().spacegroup_cache().cache( spgr_descr );
  symops  = &(cacheref.data().symops[0]);
  isymops = &(cacheref.data().isymops[0]);
  nsym  = cacheref.data().nsym;
  nsymn = cacheref.data().nsymn;
  nsymi = cacheref.data().nsymi;
  nsymc = cacheref.data().nsymc;
  nsymp = cacheref.data().nsymp;
  asufn = data::lgdata[cacheref.data().lgrp].asufn;
}
