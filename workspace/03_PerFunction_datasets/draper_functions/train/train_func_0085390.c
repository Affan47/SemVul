print_clause(omp_kind cls_kind)
{
    switch( cls_kind ){
    case OMP_CLAUSE_NOWAIT :
        fprintf(stderr," OMP_CLAUSE_NOWAIT (%d)",cls_kind);break;
    case OMP_CLAUSE_PRIVATE :
        fprintf(stderr," OMP_CLAUSE_PRIVATE (%d)",cls_kind);break;
    case OMP_CLAUSE_SHARED :
        fprintf(stderr," OMP_CLAUSE_SHARED (%d)",cls_kind);break;
    case OMP_CLAUSE_FIRSTPRIVATE :
        fprintf(stderr," OMP_CLAUSE_FIRSTPRIVATE (%d)",cls_kind);break;
    case OMP_CLAUSE_LASTPRIVATE :
        fprintf(stderr," OMP_CLAUSE_LASTPRIVATE (%d)",cls_kind);break;
    case OMP_CLAUSE_COPYIN :
        fprintf(stderr," OMP_CLAUSE_COPYIN (%d)",cls_kind);break;
    case OMP_CLAUSE_DEFAULT :
        fprintf(stderr," OMP_CLAUSE_DEFAULT (%d)",cls_kind);break;
    case OMP_CLAUSE_REDUCTION :
        fprintf(stderr," OMP_CLAUSE_REDUCTION (%d)",cls_kind);break;
    case OMP_CLAUSE_SCHEDULE :
        fprintf(stderr," OMP_CLAUSE_SCHEDULE (%d)",cls_kind);break;
    case OMP_CLAUSE_IF :
        fprintf(stderr," OMP_CLAUSE_IF (%d)",cls_kind);break;
    case OMP_CLAUSE_ORDERED :
        fprintf(stderr," OMP_CLAUSE_ORDERED (%d)",cls_kind);break;
    default :break;
    }
}
