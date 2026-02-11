moveShape(ShapeRef *shape, const double xDiff, const double yDiff)
{
    Polygon newPoly = shape->polygon();
    newPoly.translate(xDiff, yDiff);

    moveShape(shape, newPoly);
}
