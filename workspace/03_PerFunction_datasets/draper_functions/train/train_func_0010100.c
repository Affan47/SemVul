print_array(ostream &out, unsigned int index, unsigned int dims, unsigned int shape[])
{
    if (dims == 1) {
        out << "{";
        for (unsigned i = 0; i < shape[0] - 1; ++i) {
            dynamic_cast<TestCommon&> (*var(index++)).output_values(out);
            out << ", ";
        }
        dynamic_cast<TestCommon&> (*var(index++)).output_values(out);
        out << "}";

        return index;
    }
    else {
        out << "{";


        for (unsigned i = 0; i < shape[0] - 1; ++i) {
            index = print_array(out, index, dims - 1, shape + 1);
            out << ",";
        }
        index = print_array(out, index, dims - 1, shape + 1);
        out << "}";

        return index;
    }
}
