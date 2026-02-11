evry_history_init(void)
{
#undef T
#undef D
   hist_item_edd = E_CONFIG_DD_NEW("History_Item", History_Item);
#define T History_Item
#define D hist_item_edd
   E_CONFIG_VAL(D, T, plugin, STR);
   E_CONFIG_VAL(D, T, context, STR);
   E_CONFIG_VAL(D, T, input, STR);
   E_CONFIG_VAL(D, T, last_used, DOUBLE);
   E_CONFIG_VAL(D, T, usage, DOUBLE);
   E_CONFIG_VAL(D, T, count, INT);
   E_CONFIG_VAL(D, T, transient, INT);
   E_CONFIG_VAL(D, T, data, STR);
#undef T
#undef D
   hist_entry_edd = E_CONFIG_DD_NEW("History_Entry", History_Entry);
#define T History_Entry
#define D hist_entry_edd
   E_CONFIG_LIST(D, T, items, hist_item_edd);
#undef T
#undef D
   hist_types_edd = E_CONFIG_DD_NEW("History_Types", History_Types);
#define T History_Types
#define D hist_types_edd
   E_CONFIG_HASH(D, T, types, hist_entry_edd);
#undef T
#undef D
   hist_edd = E_CONFIG_DD_NEW("History", Evry_History);
#define T Evry_History
#define D hist_edd
   E_CONFIG_VAL(D, T, version, INT);
   E_CONFIG_VAL(D, T, begin, DOUBLE);
   E_CONFIG_HASH(D, T, subjects, hist_types_edd);
#undef T
#undef D
}
