clone(ClonePolicy<Function>& pol) const
{
   LValue *that = new_LValue(pol.context(), reg.file);

   pol.set<Value>(this, that);

   that->reg.size = this->reg.size;
   that->reg.type = this->reg.type;
   that->reg.data = this->reg.data;

   return that;
}
