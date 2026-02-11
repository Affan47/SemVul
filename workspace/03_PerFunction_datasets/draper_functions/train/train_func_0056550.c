operator==(const TagDetails& td, const LensTypeAndFocalLength& ltfl) {
        return (   td.val_ == ltfl.lensType_
                && std::string(td.label_).find(ltfl.focalLength_) != std::string::npos);
    }
