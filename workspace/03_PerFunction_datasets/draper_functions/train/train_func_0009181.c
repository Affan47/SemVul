on_identity_added (GoaIdentityManager *identity_manager,
                   GoaIdentity        *identity,
                   GoaIdentityService *self)
{
  GoaObject *object;
  const char *identifier;

  export_identity (self, identity);

  identifier = goa_identity_get_identifier (identity);

  object = find_object_with_principal (self, identifier, FALSE);

  if (object == NULL)
    add_temporary_account (self, identity);
}
