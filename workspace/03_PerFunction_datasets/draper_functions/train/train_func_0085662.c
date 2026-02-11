intersects(const Ray& ray,
        const list<Plane>::type& planes, bool normalIsOutside)
    {
        list<Plane>::type::const_iterator planeit, planeitend;
        planeitend = planes.end();
        bool allInside = true;
        std::pair<bool, Real> ret;
        std::pair<bool, Real> end;
        ret.first = false;
        ret.second = 0.0f;
        end.first = false;
        end.second = 0;


        Plane::Side outside = normalIsOutside ? Plane::POSITIVE_SIDE : Plane::NEGATIVE_SIDE;

        for (planeit = planes.begin(); planeit != planeitend; ++planeit)
        {
            const Plane& plane = *planeit;

            if (plane.getSide(ray.getOrigin()) == outside)
            {
                allInside = false;

                std::pair<bool, Real> planeRes =
                    ray.intersects(plane);
                if (planeRes.first)
                {

                    ret.first = true;

                    ret.second = std::max(ret.second, planeRes.second);
                }
                else
                {
                    ret.first =false;
                    ret.second=0.0f;
                    return ret;
                }
            }
            else
            {
                std::pair<bool, Real> planeRes =
                    ray.intersects(plane);
                if (planeRes.first)
                {
                    if( !end.first )
                    {
                        end.first = true;
                        end.second = planeRes.second;
                    }
                    else
                    {
                        end.second = std::min( planeRes.second, end.second );
                    }

                }

            }
        }

        if (allInside)
        {

            ret.first = true;
            ret.second = 0.0f;
            return ret;
        }

        if( end.first )
        {
            if( end.second < ret.second )
            {
                ret.first = false;
                return ret;
            }
        }
        return ret;
    }
