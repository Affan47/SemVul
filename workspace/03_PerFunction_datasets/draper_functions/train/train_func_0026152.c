IntrInfoMiddle( void )
{

    Obj selectors;
    Obj level;
    Obj selected;


    if ( IntrReturning > 0 ) { return; }
    if ( IntrIgnoring  > 0 ) { IntrIgnoring++; return; }
    if ( IntrCoding    > 0 ) { CodeInfoMiddle(); return; }


    level = PopObj();
    selectors = PopObj();
    selected = CALL_2ARGS( InfoDecision, selectors, level);
    if (selected == False)
      IntrIgnoring = 1;
    return;
}
