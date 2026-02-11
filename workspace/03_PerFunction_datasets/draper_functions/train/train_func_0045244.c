get_architecture (pIIR_EntityDeclaration entity,
		       pIIR_TextLiteral arch)
{
  pIIR_ArchitectureDeclaration arch_decl = NULL;

  vaul_design_unit *du =
    pool->get_architecture (entity->library_name->text.to_chars (),
			    entity->declarator->text.to_chars (),
			    arch->text.to_chars ());
  if (du == NULL)
    error ("unknown architecture %n(%n)", entity, arch);
  else if (du->is_error())
    error ("%n(%n): %s", entity, arch, du->get_error_desc());
  else if (du->get_tree() == NULL
	   || !du->get_tree()->is(IR_ARCHITECTURE_DECLARATION))


    error ("%n(%n) is not an architecture (??""?)", entity, arch);
  else
    {
      use_unit (du);
      arch_decl = pIIR_ArchitectureDeclaration(du->get_tree());
    }
  release_ref(du);
  return arch_decl;
}
