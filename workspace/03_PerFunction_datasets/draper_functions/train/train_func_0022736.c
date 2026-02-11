gt_toolbox_add_hidden_tool(GtToolbox *tb, const char *toolname,
                                GtTool *tool)
{
  GtToolinfo *toolinfo;
  gt_assert(tb && tb->tools);
  toolinfo = gt_toolinfo_new();
  toolinfo->tool= tool;
  toolinfo->hidden = true;
  gt_hashmap_add(tb->tools, (char*) toolname, toolinfo);
}
