Color_cmp( const Color *pColA, const Color *pColB ) {
    return Eq( pColA->r, pColB->r, M_EPS ) && Eq( pColA->g, pColB->g, M_EPS ) && Eq( pColA->b, pColB->b, M_EPS ) && Eq( pColA->a, pColB->a, M_EPS );
}
