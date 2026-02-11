clone(ClonePolicy<Function>& pol, Instruction *i) const
{
   FlowInstruction *flow = (i ? static_cast<FlowInstruction *>(i) :
                            new_FlowInstruction(pol.context(), op, NULL));

   Instruction::clone(pol, flow);
   flow->allWarp = allWarp;
   flow->absolute = absolute;
   flow->limit = limit;
   flow->builtin = builtin;

   if (builtin)
      flow->target.builtin = target.builtin;
   else
   if (op == OP_CALL)
      flow->target.fn = target.fn;
   else
   if (target.bb)
      flow->target.bb = pol.get<BasicBlock>(target.bb);

   return flow;
}
