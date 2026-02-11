addIndices(const hsTArray<unsigned short>& indices) {
    fIdxBuffCounts.append(indices.getSize());
    fIdxBuffStorage.append(new unsigned short[indices.getSize()]);
    size_t idx = fIdxBuffStorage.getSize() - 1;

    for (size_t i=0; i<fIdxBuffCounts[idx]; i++)
        fIdxBuffStorage[idx][i] = indices[i];
}
