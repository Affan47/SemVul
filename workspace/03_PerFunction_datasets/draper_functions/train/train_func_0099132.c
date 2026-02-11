fill(std::vector<std::complex<float> >& outArray, const std::vector<std::complex<double> >& inArray,
                        size_t first, size_t last)
	{

                size_t range = last - first + 1;
                if (outArray.size() != range) outArray.resize(range);
                for (size_t j = first - 1; j < last; ++j)
                {
                        outArray[j - first + 1] = std::complex<float>(inArray[j].real(),
                                                inArray[j].imag());
                }
	}
