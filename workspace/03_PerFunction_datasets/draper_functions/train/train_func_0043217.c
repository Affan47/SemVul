initialise_model_settings(Level *level, Model_settings *ms) {
#define INT_SETTING(x)    { #x, LEVEL_INT,      {i:    &ms->x}}
#define INT32_SETTING(x)  { #x, LEVEL_INT32_T,  {i32: &ms->x}}
#define VECTOR_SETTING(x) { #x, LEVEL_VECTOR,   {v:    ms->x }}
  Level_setting *sobj;
  int x;
  int nrsettings;
  settingstranslation settings_table[] = {
       INT_SETTING    (spawn_powerups),
       INT_SETTING    (spawn_constant),
       INT_SETTING    (spawn_deliver),
       INT_SETTING    (spawn_hit),
       INT_SETTING    (spawn_pickup_powerup),
       INT32_SETTING  (init_food_spawn),
       INT32_SETTING  (spawn_delay),
       INT32_SETTING  (spawn_constant_delay),
       INT32_SETTING  (random_seed),
       VECTOR_SETTING (gravity),
       VECTOR_SETTING (bounciness),
       INT32_SETTING  (player_max_life),
       INT32_SETTING  (player_ground_friction),
       INT32_SETTING  (player_air_friction),
       INT32_SETTING  (player_ground_accel),
       INT32_SETTING  (player_air_accel),
       VECTOR_SETTING (player_max_speed),
       INT32_SETTING  (foodstack_size),
       INT32_SETTING  (powerup_length),
       INT32_SETTING  (unconc_length),
       INT32_SETTING  (food_ground_friction),
       INT32_SETTING  (food_air_friction),
       VECTOR_SETTING (food_max_speed),
       INT32_SETTING  (food_deliver_life),
       INT32_SETTING  (min_food),
       INT32_SETTING  (max_food),
       VECTOR_SETTING (food_throw_speed),
       VECTOR_SETTING (player_jump_speed),
       INT32_SETTING  (starvation_delay),
       INT32_SETTING  (starvation_amount)
     };

  nrsettings = sizeof(settings_table)/sizeof(settingstranslation);

  while(((sobj = level_next_setting(level))) != NULL) {
    for ( x = 0 ; x < nrsettings; x++) {
      if (!strcmp(settings_table[x].name,sobj->name)) {
        if (sobj->type != settings_table[x].type) {
          WARN("Invalid type for setting %s",sobj->name);
        } else {
          switch (sobj->type) {
            case LEVEL_VECTOR:
              settings_table[x].target.v->x = sobj->data.vval->x;
              settings_table[x].target.v->y = sobj->data.vval->y;
              MDEBUG("Setting %s to (%d,%d)",sobj->name,
                                            sobj->data.vval->x,
                                            sobj->data.vval->y);
              break;
            case LEVEL_INT:
              *(settings_table[x].target.i) = sobj->data.ival;
              MDEBUG("Setting %s to %d",sobj->name,sobj->data.ival);
              break;
            case LEVEL_INT32_T:
              *(settings_table[x].target.i32) = sobj->data.i32val;
              MDEBUG("Setting %s to %d",sobj->name,sobj->data.i32val);
              break;
            default:
              assert (FALSE && "Unknown settings type");
          }

        }
        break;
      }
    }
  }
}
