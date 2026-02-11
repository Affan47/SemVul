convertbddcircuitabl( BddCircuit, BddNode )

  bddcircuit *BddCircuit;
  bddnode    *BddNode;
{
  ablexpr *Expr;

  setbddlocalcircuit( BddCircuit );

  Expr = convertbddnodeabl( (bddsystem *)0,
                            BddLocalCircuit->NAME_IN,
                            BddLocalCircuit->INDEX_IN, BddNode );

  loc_stablebddcircuitabl( Expr );

  return( Expr );
}
