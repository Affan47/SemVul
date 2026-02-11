moveInDirection(const WFMath::Vector<3>& vel)
{
    const double MIN_VELOCITY = 1e-3;

    Anonymous arg;

    arg->setId(m_entityId);
    arg->setAttr("velocity", vel.toAtlas());

    WFMath::CoordType sqr_mag = vel.sqrMag();
    if(sqr_mag > MIN_VELOCITY) {
        WFMath::Quaternion q;
        WFMath::CoordType z_squared = vel.z() * vel.z();
        WFMath::CoordType plane_sqr_mag = sqr_mag - z_squared;
        if(plane_sqr_mag < WFMATH_EPSILON * z_squared) {

            q.rotation(1, vel[2] > 0 ? -WFMath::Pi/2 : WFMath::Pi/2);
        } else {

            q.rotation(2, std::atan2(vel[1], vel[0]));

            q = WFMath::Quaternion(1, -std::asin(vel[2] / std::sqrt(plane_sqr_mag))) * q;
        }

        arg->setAttr("orientation", q.toAtlas());
    }

    Move moveOp;
    moveOp->setFrom(m_entityId);
    moveOp->setArgs1(arg);

    getConnection()->send(moveOp);
}
