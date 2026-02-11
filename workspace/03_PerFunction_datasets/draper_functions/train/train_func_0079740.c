irmo_struct_member_get_string(IrmoStructMember *member, void *structure)
{
        char **member_value;

        irmo_return_val_if_fail(member->size == sizeof(char *), NULL);

        member_value = MEMBER_PTR(member, structure);

        return *member_value;
}
