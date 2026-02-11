getJointName (dxJoint *j)
{
    switch (j->type()) {
    case dJointTypeBall: return "ball";
    case dJointTypeHinge: return "hinge";
    case dJointTypeSlider: return "slider";
    case dJointTypeContact: return "contact";
    case dJointTypeUniversal: return "universal";
    case dJointTypeHinge2: return "ODE_hinge2";
    case dJointTypeFixed: return "fixed";
    case dJointTypeNull: return "null";
    case dJointTypeAMotor: return "ODE_angular_motor";
    case dJointTypeLMotor: return "ODE_linear_motor";
    case dJointTypePR: return "PR";
    case dJointTypePU: return "PU";
    case dJointTypePiston: return "piston";
    default: return "unknown";
    }
}
