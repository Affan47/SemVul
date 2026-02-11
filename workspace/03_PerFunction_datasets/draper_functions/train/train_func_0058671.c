CreateTruelightOps(OpRcPtrVec & ops,
                            const TruelightTransform & data,
                            TransformDirection direction)
    {
        ops.push_back(OpRcPtr(new TruelightOp(data.getConfigRoot(),
                                              data.getProfile(),
                                              data.getCamera(),
                                              data.getInputDisplay(),
                                              data.getRecorder(),
                                              data.getPrint(),
                                              data.getLamp(),
                                              data.getOutputCamera(),
                                              data.getDisplay(),
                                              data.getCubeInput(),
                                              direction)));
    }
