EvalVarRef(const StringExpression *expr, VarRefEvaluator evalfn,
                        void *param)
{
char *name, *eval;

name = EvalStringExpression(expr->val.varref.name, evalfn, param);
if (!name)
   {
   return NULL;
   }

eval = (*evalfn)(name, param);
free(name);
return eval;
}
