misc_draw(hwloc_topology_t topology, struct draw_methods *methods, int logical, hwloc_obj_t level, void *output, unsigned depth, unsigned x, unsigned *retwidth, unsigned y, unsigned *retheight)
{
  unsigned boxheight = gridsize + (fontsize ? (fontsize + gridsize) : 0);
  unsigned myheight = boxheight + (level->arity?gridsize:0), totheight;
  unsigned mywidth = 0, totwidth;
  unsigned textwidth = level->name ? strlen(level->name) * fontsize : 6*fontsize;
  int vert = prefer_vert(topology, logical, level, output, depth, x, y, gridsize);
  struct style style;

  DYNA_CHECK();

  if (level->arity > 1 && (level->children[0]->type == HWLOC_OBJ_MACHINE || !level->children[0]->cpuset))
    NETWORK_DRAW_BEGIN();
  else
    RECURSE_HORIZ(level, &null_draw_methods, gridsize, 0);

  lstopo_set_object_color(methods, topology, level, 0, &style);
  methods->box(output, style.bg.r, style.bg.g, style.bg.b, depth, x, totwidth, y, boxheight);

  if (fontsize) {
    if (level->name) {
      methods->text(output, style.t.r, style.t.g, style.t.b, fontsize, depth-1, x + gridsize, y + gridsize, level->name);
    } else {
      char text[64];
      lstopo_obj_snprintf(text, sizeof(text), level, logical);
      methods->text(output, style.t.r, style.t.g, style.t.b, fontsize, depth-1, x + gridsize, y + gridsize, text);
    }
  }

  if (level->arity > 1 && (level->children[0]->type == HWLOC_OBJ_MACHINE || !level->children[0]->cpuset))
    NETWORK_DRAW_END();
  else
    RECURSE_HORIZ(level, methods, gridsize, 0);

  DYNA_SAVE();
}
