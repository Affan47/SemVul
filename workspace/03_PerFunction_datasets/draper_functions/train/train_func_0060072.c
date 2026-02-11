FreeStringExpression(StringExpression *expr)
{
if (!expr)
   {
   return;
   }

switch (expr->op)
   {
   case CONCAT:
      FreeStringExpression(expr->val.concat.lhs);
      FreeStringExpression(expr->val.concat.rhs);
      break;
   case LITERAL:
      free(expr->val.literal.literal);
      break;
   case VARREF:
      FreeStringExpression(expr->val.varref.name);
      break;
   default:
      FatalError("Unknown type of string expression encountered: %d",
                 expr->op);
   }

free(expr);
}
