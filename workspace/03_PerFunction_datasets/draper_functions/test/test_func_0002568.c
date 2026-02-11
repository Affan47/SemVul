OutputBranch(bool,  TIntermBranch* node, TIntermTraverser* it)
{
   TOutputTraverser* oit = static_cast<TOutputTraverser*>(it);
   TInfoSink& out = oit->infoSink;

   OutputTreeText(out, node, oit->depth);

   switch (node->getFlowOp())
   {
   case EOpKill:      out.debug << "Branch: Kill";           break;
   case EOpBreak:     out.debug << "Branch: Break";          break;
   case EOpContinue:  out.debug << "Branch: Continue";       break;
   case EOpReturn:    out.debug << "Branch: Return";         break;
   default:               out.debug << "Branch: Unknown Branch"; break;
   }

   if (node->getExpression())
   {
      out.debug << " with expression\n";
      ++oit->depth;
      node->getExpression()->traverse(it);
      --oit->depth;
   }
   else
      out.debug << "\n";

   return false;
}
