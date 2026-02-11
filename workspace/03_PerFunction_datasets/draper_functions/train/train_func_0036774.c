WriteCreate(const MoveSpline& move_spline, ByteBuffer& data)
    {


        {
            MoveSplineFlag splineFlags = move_spline.splineflags;

            data << splineFlags.raw();

            if (splineFlags.final_angle)
            {
                data << move_spline.facing.angle;
            }
            else if (splineFlags.final_target)
            {
                data << move_spline.facing.target;
            }
            else if (splineFlags.final_point)
            {
                data << move_spline.facing.f.x << move_spline.facing.f.y << move_spline.facing.f.z;
            }

            data << move_spline.timePassed();
            data << move_spline.Duration();
            data << move_spline.GetId();

            uint32 nodes = move_spline.getPath().size();
            data << nodes;
            data.append<Vector3>(&move_spline.getPath()[0], nodes);
            data << (move_spline.isCyclic() ? Vector3::zero() : move_spline.FinalDestination());
        }
    }
