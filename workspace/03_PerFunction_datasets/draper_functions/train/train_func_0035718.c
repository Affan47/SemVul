blowfish_start(Function *global_funcs)
{
  int i;


  if (global_funcs) {
    global = global_funcs;

    if (!module_rename("blowfish", MODULE_NAME))
      return "Already loaded.";

    for (i = 0; i < BOXES; i++) {
      box[i].P = NULL;
      box[i].S = NULL;
      box[i].key[0] = 0;
      box[i].lastuse = 0L;
    }
    module_register(MODULE_NAME, blowfish_table, 2, 1);
    if (!module_depend(MODULE_NAME, "eggdrop", 106, 3)) {
      module_undepend(MODULE_NAME);
      return "This module requires Eggdrop 1.6.3 or later.";
    }
    add_hook(HOOK_ENCRYPT_PASS, (Function) blowfish_encrypt_pass);
    add_hook(HOOK_ENCRYPT_STRING, (Function) encrypt_string);
    add_hook(HOOK_DECRYPT_STRING, (Function) decrypt_string);
  }
  add_tcl_commands(mytcls);
  return NULL;
}
