create_func_not(MY_XPATH *xpath, Item **args, uint nargs)
{
  return new Item_func_not(nodeset2bool(xpath, args[0]));
}
