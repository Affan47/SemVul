genie_declaration (NODE_T * p)
{
  for (; p != NO_NODE; FORWARD (p)) {
    switch (ATTRIBUTE (p)) {
    case MODE_DECLARATION:
    case PROCEDURE_DECLARATION:
    case BRIEF_OPERATOR_DECLARATION:
    case PRIORITY_DECLARATION:
      {

        return;
      }
    case IDENTITY_DECLARATION:
      {
        genie_identity_dec (SUB (p));
        break;
      }
    case OPERATOR_DECLARATION:
      {
        genie_operator_dec (SUB (p));
        break;
      }
    case VARIABLE_DECLARATION:
      {
        NODE_T *declarer = NO_NODE;
        ADDR_T pop_sp = stack_pointer;
        genie_variable_dec (SUB (p), &declarer, stack_pointer);

        stack_pointer = pop_sp;
        break;
      }
    case PROCEDURE_VARIABLE_DECLARATION:
      {
        ADDR_T pop_sp = stack_pointer;
        genie_proc_variable_dec (SUB (p));
        stack_pointer = pop_sp;
        break;
      }
    default:
      {
        genie_declaration (SUB (p));
        break;
      }
    }
  }
}
