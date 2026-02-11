midgard_core_query_constraint_add_sql(
                MidgardCoreQueryConstraint *constraint, GString *sql) {
        g_assert(constraint);
        g_assert(sql);
        MIDGARD_CORE_QUERY_CONSTRAINT_GET_CLASS(constraint)->add_sql(constraint, sql);
}
