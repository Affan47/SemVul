operator()(const G3D::Ray& ray, uint32 entry, float& distance, bool pStopAtFirstHit = true)
            {
                bool result = prims[entry].intersectRay(ray, distance, pStopAtFirstHit);
                if (result)
                    { hit = true; }
                return result;
            }
