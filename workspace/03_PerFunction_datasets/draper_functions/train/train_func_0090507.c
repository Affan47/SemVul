BuildGuide(const dawgdic::Dawg &dawg,
                const dawgdic::Dictionary &dic, dawgdic::Guide *guide) {
  if (!dawgdic::GuideBuilder::Build(dawg, dic, guide)) {
    std::cerr << "failed to build Guide" << std::endl;
    return false;
  }

  std::cerr << "no. units: " << guide->size() << std::endl;
  std::cerr << "guide size: " << guide->total_size() << std::endl;

  return true;
}

}
