delbddnodelist( BddSystem, HeadList )

  bddsystem  *BddSystem;
  chain_list *HeadList;
{
  chain_list  *ScanList;

  setbddlocalsystem( BddSystem );

  for ( ScanList  = HeadList;
        ScanList != (chain_list *)0;
        ScanList  = ScanList->NEXT )
  {
    decbddrefext( (bddnode *)ScanList->DATA );
  }

  freechain( HeadList );
}
