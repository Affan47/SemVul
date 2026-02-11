constructArrayFromAxistags(python::object type, ArrayVector<npy_intp> const & shape,
                           NPY_TYPES typeCode, AxisTags const & axistags, bool init)
{
    PyAxisTags pyaxistags(python_ptr(python::object(axistags).ptr()));

    ArrayVector<npy_intp> norm_shape(shape);
    if(pyaxistags.size() > 0)
    {
        ArrayVector<npy_intp> permutation(pyaxistags.permutationToNormalOrder());
        applyPermutation(permutation.begin(), permutation.end(), shape.begin(), norm_shape.begin());
    }

    TaggedShape tagged_shape(norm_shape, pyaxistags);

    return constructArray(tagged_shape, typeCode, init, python_ptr(type.ptr()));
}
