processNode(const BspNode* node, const Ray& tracingRay,
        RaySceneQueryListener* listener, Real maxDistance, Real traceDistance)
    {
        if (node->isLeaf())
        {
            return processLeaf(node, tracingRay, listener, maxDistance, traceDistance);
        }

        bool res = true;
        std::pair<bool, Real> result = tracingRay.intersects(node->getSplitPlane());
        if (result.first && result.second < maxDistance)
        {


            Vector3 splitPoint = tracingRay.getOrigin()
                + tracingRay.getDirection() * result.second;
            Ray splitRay(splitPoint, tracingRay.getDirection());

            if (node->getSide(tracingRay.getOrigin()) == Plane::NEGATIVE_SIDE)
            {

                res = processNode(
                    node->getBack(), tracingRay, listener, result.second, traceDistance);
                if (!res) return res;

                res = processNode(
                    node->getFront(), splitRay, listener,
                    maxDistance - result.second,
                    traceDistance + result.second);
            }
            else
            {

                res = processNode(node->getFront(), tracingRay, listener,
                    result.second, traceDistance);
                if (!res) return res;
                res = processNode(node->getBack(), splitRay, listener,
                    maxDistance - result.second,
                    traceDistance + result.second);
            }
        }
        else
        {

            res = processNode(node->getNextNode(tracingRay.getOrigin()),
                tracingRay, listener, maxDistance, traceDistance);
        }

        return res;
    }
