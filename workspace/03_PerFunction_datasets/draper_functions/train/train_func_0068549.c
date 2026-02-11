get_access_flags_from_decl (tree decl)
{
  int access_flags = 0;
  if (TREE_CODE (decl) == FIELD_DECL || TREE_CODE (decl) == VAR_DECL)
    {
      if (FIELD_STATIC (decl))
	access_flags |= ACC_STATIC;
      if (FIELD_PUBLIC (decl))
	access_flags |= ACC_PUBLIC;
      if (FIELD_PROTECTED (decl))
	access_flags |= ACC_PROTECTED;
      if (FIELD_PRIVATE (decl))
	access_flags |= ACC_PRIVATE;
      if (FIELD_FINAL (decl))
	access_flags |= ACC_FINAL;
      if (FIELD_VOLATILE (decl))
	access_flags |= ACC_VOLATILE;
      if (FIELD_TRANSIENT (decl))
	access_flags |= ACC_TRANSIENT;
      if (FIELD_ENUM (decl))
	access_flags |= ACC_ENUM;
      if (FIELD_SYNTHETIC (decl))
	access_flags |= ACC_SYNTHETIC;
      return access_flags;
    }
  if (TREE_CODE (decl) == TYPE_DECL)
    {
      if (CLASS_PUBLIC (decl))
	access_flags |= ACC_PUBLIC;
      if (CLASS_FINAL (decl))
	access_flags |= ACC_FINAL;
      if (CLASS_SUPER (decl))
	access_flags |= ACC_SUPER;
      if (CLASS_INTERFACE (decl))
	access_flags |= ACC_INTERFACE;
      if (CLASS_ABSTRACT (decl))
	access_flags |= ACC_ABSTRACT;
      if (CLASS_STATIC (decl))
	access_flags |= ACC_STATIC;
      if (CLASS_PRIVATE (decl))
	access_flags |= ACC_PRIVATE;
      if (CLASS_PROTECTED (decl))
	access_flags |= ACC_PROTECTED;
      if (CLASS_STRICTFP (decl))
	access_flags |= ACC_STRICT;
      if (CLASS_ENUM (decl))
	access_flags |= ACC_ENUM;
      if (CLASS_SYNTHETIC (decl))
	access_flags |= ACC_SYNTHETIC;
      if (CLASS_ANNOTATION (decl))
	access_flags |= ACC_ANNOTATION;
      return access_flags;
    }
  if (TREE_CODE (decl) == FUNCTION_DECL)
    {
      if (METHOD_PUBLIC (decl))
	access_flags |= ACC_PUBLIC;
      if (METHOD_PRIVATE (decl))
	access_flags |= ACC_PRIVATE;
      if (METHOD_PROTECTED (decl))
	access_flags |= ACC_PROTECTED;
      if (METHOD_STATIC (decl))
	access_flags |= ACC_STATIC;
      if (METHOD_FINAL (decl))
	access_flags |= ACC_FINAL;
      if (METHOD_SYNCHRONIZED (decl))
	access_flags |= ACC_SYNCHRONIZED;
      if (METHOD_NATIVE (decl))
	access_flags |= ACC_NATIVE;
      if (METHOD_ABSTRACT (decl))
	access_flags |= ACC_ABSTRACT;
      if (METHOD_STRICTFP (decl))
	access_flags |= ACC_STRICT;
      if (METHOD_INVISIBLE (decl))
	access_flags |= ACC_INVISIBLE;
      if (DECL_ARTIFICIAL (decl))
	access_flags |= ACC_SYNTHETIC;
      if (METHOD_BRIDGE (decl))
	access_flags |= ACC_BRIDGE;
      if (METHOD_VARARGS (decl))
	access_flags |= ACC_VARARGS;
      return access_flags;
    }
  gcc_unreachable ();
}
