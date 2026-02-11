generateEigenMat4s(int count) {
    float* randomNumbers = generateRandomNumbers(count);

    Eigen::Matrix4f* eigenmats = new Eigen::Matrix4f[count];
    for(int i = 0; i < count; i++) {
        eigenmats[i](0,0) = randomNumbers[i];
        eigenmats[i](1,1) = randomNumbers[i];
        eigenmats[i](2,2) = randomNumbers[i];
        eigenmats[i](3,3) = 1.0f;
    }

    delete[] randomNumbers;

    return eigenmats;
}
