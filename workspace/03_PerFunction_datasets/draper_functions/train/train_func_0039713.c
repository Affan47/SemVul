RETWRAP (int ret)
  {
    if (ret < 0)
      throw (exception (ret));
    return ret;
  }
