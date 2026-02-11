add_implicitly_declared_members (tree t, tree* access_decls,
				 int cant_have_const_cctor,
				 int cant_have_const_assignment)
{
  bool move_ok = false;

  if (cxx_dialect >= cxx0x && !CLASSTYPE_DESTRUCTORS (t)
      && !TYPE_HAS_COPY_CTOR (t) && !TYPE_HAS_COPY_ASSIGN (t)
      && !type_has_move_constructor (t) && !type_has_move_assign (t))
    move_ok = true;


  if (!CLASSTYPE_DESTRUCTORS (t))
    {

      CLASSTYPE_LAZY_DESTRUCTOR (t) = 1;

      if (TYPE_HAS_NONTRIVIAL_DESTRUCTOR (t)
	  && TYPE_FOR_JAVA (t))


	lazily_declare_fn (sfk_destructor, t);
    }


  if (! TYPE_HAS_USER_CONSTRUCTOR (t))
    {
      TYPE_HAS_DEFAULT_CONSTRUCTOR (t) = 1;
      CLASSTYPE_LAZY_DEFAULT_CTOR (t) = 1;
      if (cxx_dialect >= cxx0x)
	TYPE_HAS_CONSTEXPR_CTOR (t)

	  = type_has_constexpr_default_constructor (t);
    }


  if (! TYPE_HAS_COPY_CTOR (t) && ! TYPE_FOR_JAVA (t))
    {
      TYPE_HAS_COPY_CTOR (t) = 1;
      TYPE_HAS_CONST_COPY_CTOR (t) = !cant_have_const_cctor;
      CLASSTYPE_LAZY_COPY_CTOR (t) = 1;
      if (move_ok)
	CLASSTYPE_LAZY_MOVE_CTOR (t) = 1;
    }


  if (!TYPE_HAS_COPY_ASSIGN (t) && !TYPE_FOR_JAVA (t))
    {
      TYPE_HAS_COPY_ASSIGN (t) = 1;
      TYPE_HAS_CONST_COPY_ASSIGN (t) = !cant_have_const_assignment;
      CLASSTYPE_LAZY_COPY_ASSIGN (t) = 1;
      if (move_ok)
	CLASSTYPE_LAZY_MOVE_ASSIGN (t) = 1;
    }


  declare_virt_assop_and_dtor (t);

  while (*access_decls)
    {
      tree using_decl = TREE_VALUE (*access_decls);
      tree decl = USING_DECL_DECLS (using_decl);
      if (DECL_NAME (using_decl) == ctor_identifier)
	{

	  tree ctor_list = decl;
	  location_t loc = input_location;
	  input_location = DECL_SOURCE_LOCATION (using_decl);
	  if (ctor_list)
	    for (; ctor_list; ctor_list = OVL_NEXT (ctor_list))
	      one_inherited_ctor (OVL_CURRENT (ctor_list), t);
	  *access_decls = TREE_CHAIN (*access_decls);
	  input_location = loc;
	}
      else
	access_decls = &TREE_CHAIN (*access_decls);
    }
}
