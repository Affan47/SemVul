set_combat_level(int combatLevel)
{
	err_when( combatLevel<=0 || combatLevel>100 );

   skill.combat_level = combatLevel;

   UnitInfo* unitInfo = unit_res[unit_id];

   int oldMaxHitPoints = max_hit_points;

   max_hit_points = unitInfo->hit_points * combatLevel / 100;

   hit_points = hit_points * max_hit_points / oldMaxHitPoints;

   hit_points = MIN(hit_points, max_hit_points);


   if( combatLevel >= unitInfo->guard_combat_level)
   {
      can_guard_flag = sprite_info->can_guard_flag;
		if( unit_id == UNIT_ZULU )
			can_guard_flag |= 4;
   }
   else
   {
      can_guard_flag = 0;
   }

   max_power = skill.combat_level + 50;
   cur_power = MIN(cur_power, max_power);
}
