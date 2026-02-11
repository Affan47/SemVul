ComputeQuadQuality (vtkCell* cell)
{
  switch (this->GetQualityMeasure())
    {
    case AREA:           return vtkMeshQuality::QuadArea(cell);
    case ASPECT_RATIO:   return vtkMeshQuality::QuadAspectRatio(cell);
    case CONDITION:      return vtkMeshQuality::QuadCondition(cell);
    case DISTORTION:     return vtkMeshQuality::QuadDistortion(cell);
    case EDGE_RATIO:     return vtkMeshQuality::QuadEdgeRatio(cell);
    case JACOBIAN:       return vtkMeshQuality::QuadJacobian(cell);
    case MAX_ANGLE:      return vtkMeshQuality::QuadMaxAngle(cell);
    case MAX_ASPECT_FROBENIUS:
      return vtkMeshQuality::QuadMaxAspectFrobenius(cell);
    case MAX_EDGE_RATIO: return vtkMeshQuality::QuadMaxEdgeRatios(cell);
    case MED_ASPECT_FROBENIUS:
      return vtkMeshQuality::QuadMedAspectFrobenius(cell);
    case MIN_ANGLE:      return vtkMeshQuality::QuadMinAngle(cell);
    case ODDY:           return vtkMeshQuality::QuadOddy(cell);
    case RADIUS_RATIO:   return vtkMeshQuality::QuadRadiusRatio(cell);
    case RELATIVE_SIZE_SQUARED:
      return vtkMeshQuality::QuadRelativeSizeSquared(cell);
    case SCALED_JACOBIAN:return vtkMeshQuality::QuadScaledJacobian(cell);
    case SHAPE_AND_SIZE: return vtkMeshQuality::QuadShapeAndSize(cell);
    case SHAPE:          return vtkMeshQuality::QuadShape(cell);
    case SHEAR_AND_SIZE: return vtkMeshQuality::QuadShearAndSize(cell);
    case SHEAR:          return vtkMeshQuality::QuadShear(cell);
    case SKEW:           return vtkMeshQuality::QuadSkew(cell);
    case STRETCH:        return vtkMeshQuality::QuadStretch(cell);
    case TAPER:          return vtkMeshQuality::QuadTaper(cell);
    case WARPAGE:        return vtkMeshQuality::QuadWarpage(cell);
    default:             return this->GetUndefinedQuality();
    }
}
