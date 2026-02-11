AddDistanceConstraint(int a, int b, double length)
  {
    OBFFConstraint constraint;
    constraint.type = OBFF_CONST_DISTANCE;
    constraint.ia   = a;
    constraint.ib   = b;
    constraint.constraint_value = length;
    constraint.factor = _factor;
    _constraints.push_back(constraint);
  }
