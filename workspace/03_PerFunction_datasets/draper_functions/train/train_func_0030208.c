inv() const {
    Pose6D result(*this);
    result.rot() = rot().inv().normalized();
    result.trans() = result.rot().rotate(-trans());
    return result;
  }
