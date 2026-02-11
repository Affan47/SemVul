is_admissible_throw_operand (tree expr)
{
  tree type = TREE_TYPE (expr);


  if (!complete_ptr_ref_or_void_ptr_p (type, expr))
    return false;


  else if (CLASS_TYPE_P (type) && CLASSTYPE_PURE_VIRTUALS (type))
    {
      error ("expression '%E' of abstract class type '%T' cannot be used in throw-expression", expr, type);
      return false;
    }

  return true;
}
