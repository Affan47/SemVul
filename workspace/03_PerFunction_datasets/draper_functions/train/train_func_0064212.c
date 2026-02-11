find_color_indices(void_vector<UInt8> & data,
           std::vector<ColorCluster> & clusters, void_vector<UInt8> & indices)
    {
        size_t count = clusters.size();
        UInt8 * base = data.begin();

        size_t i;
        for(i=0; i<count; ++i)
        {
            for(size_t j=0; j<clusters[i].size(); ++j)
            {
                size_t offset = (clusters[i].entries[j] - base) / 3;
                indices[offset] = static_cast<UInt8>(i);
            }
        }
    }
