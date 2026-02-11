GetParticleVariable( scalar_t Func[5], char *name )
{
    VARIABLE *var;

    double *T;

    int i,n,index;

    var = (VARIABLE *)lst_find( VARIABLES, name );

    Func[0].f =
        Func[1].f =
        Func[2].f =
        Func[3].f =
        Func[4].f = NULL;

    if ( !var || NROW(var) != 5 ) return;

    Func[0].f = &M(var,0,0);
    Func[1].f = &M(var,1,0);
    Func[2].f = &M(var,2,0);
    Func[3].f = &M(var,3,0);
    Func[4].f = &M(var,4,0);

    ParticleNofParticles = NCOL(var);
}
