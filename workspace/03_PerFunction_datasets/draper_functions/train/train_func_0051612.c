compileInits(Interpreter &interp,
					const Environment &env,
					const BoundVarList &initVars,
					size_t initIndex,
					int stackPos,
					const InsnPtr &next)
{
  if (initIndex >= inits_.size())
    return next;
  Environment nextEnv(env);
  BoundVarList vars;
  vars.append(initVars[initIndex].ident, initVars[initIndex].flags);
  nextEnv.augmentFrame(vars, stackPos);
  InsnPtr tem
    = compileInits(interp, nextEnv, initVars, initIndex + 1, stackPos + 1, next);
  if (initVars[initIndex].boxed())
    tem = new BoxInsn(tem);
  return optimizeCompile(inits_[initIndex], interp, env, stackPos, tem);
}
