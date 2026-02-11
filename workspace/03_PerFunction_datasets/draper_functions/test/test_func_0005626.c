indexGetter(ExecState* exec, JSObject*, const Identifier& , const PropertySlot& slot)
{
  return new Plugin(exec, plugins->at(slot.index()));
}
