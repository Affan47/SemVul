initialize_node
(
    Int k,
    Int Post [ ],
    Int Parent [ ],
    Int ColCount [ ],
    Int PrevNbr [ ]
)
{
    Int p, parent ;

    p = Post [k] ;

    parent = Parent [p] ;
    if (parent != EMPTY)
    {
	ColCount [parent]-- ;
    }

    PrevNbr [p] = k ;
    return (p) ;
}
