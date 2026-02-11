generateHistogram(const VideoFrame& videoFrame, Histogram<int>& histogram)
{
    for (int i = 0; i < videoFrame.height; ++i)
    {
        int pixelIndex = i * videoFrame.lineSize;
        for (int j = 0; j < videoFrame.width * 3; j += 3)
        {
            ++histogram.r[videoFrame.frameData[pixelIndex + j]];
            ++histogram.g[videoFrame.frameData[pixelIndex + j + 1]];
            ++histogram.b[videoFrame.frameData[pixelIndex + j + 2]];
        }
    }
}
