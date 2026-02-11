make_gun_sound_effect(game *g, player &p, bool burst)
{
 std::string gunsound;
 int noise = p.weapon.noise();
 if (noise < 5) {
  if (burst)
   gunsound = "Brrrip!";
  else
   gunsound = "plink!";
 } else if (noise < 25) {
  if (burst)
   gunsound = "Brrrap!";
  else
   gunsound = "bang!";
 } else if (noise < 60) {
  if (burst)
   gunsound = "P-p-p-pow!";
  else
   gunsound = "blam!";
 } else {
  if (burst)
   gunsound = "Kaboom!!";
  else
   gunsound = "kerblam!";
 }
 if (p.weapon.curammo->type == AT_FUSION || p.weapon.curammo->type == AT_BATT ||
     p.weapon.curammo->type == AT_PLUT)
  g->sound(p.posx, p.posy, 8, "Fzzt!");
 else if (p.weapon.curammo->type == AT_40MM)
  g->sound(p.posx, p.posy, 8, "Thunk!");
 else if (p.weapon.curammo->type == AT_GAS)
  g->sound(p.posx, p.posy, 4, "Fwoosh!");
 else if (p.weapon.curammo->type != AT_BOLT &&
          p.weapon.curammo->type != AT_ARROW)
  g->sound(p.posx, p.posy, noise, gunsound);
}
