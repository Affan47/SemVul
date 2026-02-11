midgard_group_constraint_add_constraint(
                MidgardGroupConstraint *self,
                MidgardCoreQueryConstraint *constraint)
{


        g_assert(constraint != NULL);

	self->constraints = g_slist_append(self->constraints, constraint);
}
