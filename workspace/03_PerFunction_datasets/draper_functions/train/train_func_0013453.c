setLocalScaling(const btVector3& scaling)
{
   if ((getLocalScaling() -scaling).length2() > SIMD_EPSILON)
   {
      btTriangleMeshShape::setLocalScaling(scaling);
	  buildOptimizedBvh();
   }
}
