ToString() const
    {
        std::stringstream str;
        str << "MoveSpline" << std::endl;
        str << "spline Id: " << GetId() << std::endl;
        str << "flags: " << splineflags.ToString() << std::endl;
        if (splineflags.final_angle)
            str << "facing  angle: " << facing.angle;
        else if (splineflags.final_target)
            str << "facing target: " << facing.target;
        else if (splineflags.final_point)
            str << "facing  point: " << facing.f.x << " " << facing.f.y << " " << facing.f.z;
        str << std::endl;
        str << "time passed: " << time_passed << std::endl;
        str << "total  time: " << Duration() << std::endl;
        str << "spline point Id: " << point_Idx << std::endl;
        str << "path  point  Id: " << currentPathIdx() << std::endl;
        str << spline.ToString();
        return str.str();
    }
