loc_getbddsize( BddNode )

  bddnode *BddNode;
{
  if ( BddNode->INDEX >= BDD_INDEX_MIN )
  {
    BddFlagNumberNode++;

    loc_getbddsize( BddNode->LOW  );
    loc_getbddsize( BddNode->HIGH );
  }
}
