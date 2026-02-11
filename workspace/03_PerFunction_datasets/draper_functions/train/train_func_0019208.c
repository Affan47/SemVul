sparse_vector_iter(ScmObj* args,int nargs,void* data){{
#line 252 "./sparse.scm"
{SparseVectorIter* iter=((SparseVectorIter* )(data));ScmObj r=
SparseVectorIterNext(iter);ScmObj eofval=
(args)[0];
if (SCM_FALSEP(r)){
return (Scm_Values2(eofval,eofval));} else {
return (Scm_Values2(SCM_CAR(r),SCM_CDR(r)));}}}}
