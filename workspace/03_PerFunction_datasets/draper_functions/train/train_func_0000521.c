defineGeometry()
{
    using namespace python;

    docstring_options doc_options(true, true, false);

    multidef("convexHull",
         pythonConvexHull<double, float, Int32>(),
         args("points"),
        "Compute the convex hull of a point set.\n"
        "\n"
        "For details see convexHull_ in the vigra C++ documentation.\n\n");
}
